package ft.avaj.simulation;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import ft.avaj.Bootstrap;
import ft.avaj.exception.InvalidFileFormatException;
import ft.avaj.vehicule.AircraftFactory;
import ft.avaj.vehicule.Flyable;

public class Simulation implements Runnable {
	
	private final int times;
	private final List<Flyable> flyables;
	
	private Simulation(int times, List<Flyable> flyables) {
		this.times = times;
		this.flyables = flyables;
	}
	
	@Override
	public void run() {
		WeatherTower weatherTower = new WeatherTower();
		for (Flyable flyable : flyables) {
			weatherTower.register(flyable);
		}
		
		for (int time = 0; time < times; time++) {
			weatherTower.changeWeather();
		}
	}
	
	/* The input file needs to be validated. If the input file data is not correct the program stops execution. */
	public static Simulation fromFile(File file) throws FileNotFoundException {
		/* format: TYPE NAME LONGITUDE LATITUDE HEIGHT */
		final Pattern linePattern = Pattern.compile("^(\\w+) (\\w+) (\\d+) (\\d+) (\\d+)$");
		
		try (Scanner scanner = new Scanner(file)) {
			Builder builder = builder();
			
			boolean first = true;
			int lineNumber = 1;
			
			while (scanner.hasNextLine()) {
				String line = scanner.nextLine();
				
				if (line.isEmpty()) {
					if (first) {
						throw new InvalidFileFormatException("expected the first line to be an int", lineNumber);
					}
					
					throw new InvalidFileFormatException("empty line", lineNumber);
				}
				
				if (first) {
					/* The first line of the file contains a positive integer number. */
					
					builder.times(Integer.parseInt(line));
					
					first = false;
				} else {
					/* Each following line describes an aircraft that will be part of the simulation, with this format: TYPE NAME LONGITUDE LATITUDE HEIGHT. */
					
					Matcher matcher = linePattern.matcher(line);
					if (!matcher.find()) {
						throw new InvalidFileFormatException(String.format("expected pattern `%s` but got `%s`", linePattern, line), lineNumber);
					}
					
					String type = matcher.group(1);
					String name = matcher.group(2);
					int longitude = Integer.parseInt(matcher.group(3));
					int latitude = Integer.parseInt(matcher.group(4));
					int height = Integer.parseInt(matcher.group(5));
					
					if (Bootstrap.DEBUG) {
						System.err.println(String.format("new aircraft: %15s %4s %4d %4d %4d", type, name, longitude, latitude, height));
					}
					
					Flyable flyable = AircraftFactory.newAircraft(type, name, longitude, latitude, height);
					
					builder.flyable(flyable);
				}
				
				lineNumber++;
			}
			
			return builder.build();
		}
	}
	
	public static Builder builder() {
		return new Builder();
	}
	
	public static class Builder {
		
		private int times;
		private List<Flyable> flyables;
		
		private Builder() {
			this.flyables = new ArrayList<>();
		}
		
		public Builder times(int times) {
			if (times < 0) {
				throw new IllegalArgumentException("times cannot be negative: " + times);
			}
			
			this.times = times;
			
			return this;
		}
		
		public Builder flyable(Flyable flyable) {
			this.flyables.add(flyable);
			
			return this;
		}
		
		public Simulation build() {
			return new Simulation(times, flyables);
		}
		
	}
	
}