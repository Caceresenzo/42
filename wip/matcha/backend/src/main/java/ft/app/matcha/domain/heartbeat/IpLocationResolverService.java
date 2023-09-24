package ft.app.matcha.domain.heartbeat;

import java.io.File;
import java.io.OutputStream;
import java.net.InetAddress;
import java.util.Optional;

import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;

import com.maxmind.geoip2.DatabaseReader;

import ft.app.matcha.configuration.HeartbeatConfigurationProperties;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import spark.utils.StringUtils;

@Slf4j
public class IpLocationResolverService {
	
	private final DatabaseReader reader;
	
	@SneakyThrows
	public IpLocationResolverService(OkHttpClient httpClient, HeartbeatConfigurationProperties properties) {
		final var file = new File(properties.getMaxmindGeoIpDatabasePath());
		if (!file.exists()) {
			download(httpClient, file, properties.getMaxmindLicenseKey());
		}
		
		this.reader = new DatabaseReader.Builder(file).build();
	}
	
	@SneakyThrows
	public Optional<IpLocation> resolve(InetAddress inetAddress) {
		return reader.tryCity(inetAddress)
			.map((response) -> new IpLocation(
				response.getCountry().getName(),
				response.getCity().getName(),
				response.getLocation().getLatitude(),
				response.getLocation().getLongitude()
			));
	}
	
	@SneakyThrows
	public static void download(OkHttpClient httpClient, File destination, String licenseKey) {
		log.info("Downloading GeoIP database from MAXMIND's servers...");
		
		if (StringUtils.isBlank(licenseKey)) {
			throw new IllegalArgumentException("no license key provided");
		}
		
		final var call = httpClient.newCall(new Request.Builder()
			.get()
			.url(HttpUrl.parse("https://download.maxmind.com/app/geoip_download").newBuilder()
				.addEncodedQueryParameter("edition_id", "GeoLite2-City")
				.addEncodedQueryParameter("license_key", licenseKey)
				.addEncodedQueryParameter("suffix", "tar.gz")
				.build())
			.build());
		
		try (
			final var response = call.execute();
			final var body = response.body();
			final var inputStream = body.byteStream();
			final var gzipInputStream = new GzipCompressorInputStream(inputStream);
			final var tarInputStream = new TarArchiveInputStream(gzipInputStream);
		) {
			ArchiveEntry entry = null;
			while ((entry = tarInputStream.getNextEntry()) != null) {
				final var name = entry.getName();
				log.info("Found '{}'", name);
				
				if (!name.endsWith(".mmdb")) {
					continue;
				}
				
				log.info("Storing to '{}'", destination);
				try (OutputStream outputStream = FileUtils.openOutputStream(destination)) {
					IOUtils.copy(tarInputStream, outputStream);
				}
			}
		} catch (Exception exception) {
			FileUtils.deleteQuietly(destination);
			throw exception;
		}
	}
	
}