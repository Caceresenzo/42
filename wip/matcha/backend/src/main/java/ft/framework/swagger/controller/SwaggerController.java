package ft.framework.swagger.controller;

import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.ResponseBody;
import ft.framework.util.MediaTypes;
import io.swagger.v3.core.util.Json;
import io.swagger.v3.oas.models.OpenAPI;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;

@RequiredArgsConstructor
@Controller
public class SwaggerController {
	
	private final OpenAPI swagger;
	
	@GetMapping(path = "spec.json")
	@ResponseBody
	public String spec() {
		return convertToSpec(swagger);
	}
	
	@GetMapping(produce = MediaTypes.HTML)
	@ResponseBody
	public String index() {
		return """
			<!DOCTYPE html>
			<html>
			<head>
			    <title>Docs</title>
			    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/swagger-ui-dist@3.17.0/swagger-ui.css">
			</head>
			<body>
			    <div id="ui-wrapper-new" data-spec="{{spec}}">
			        Loading....
			    </div>
			</body>
			<script src="https://unpkg.com/swagger-ui-dist@3.23.1/swagger-ui-bundle.js"></script>
			<script>
			    window.ui = SwaggerUIBundle({
			      url: "/spec.json",
			      dom_id: '#ui-wrapper-new',
			      docExpansion: 'list',
			      deepLinking: true,
			      filter: true,
			      presets: [
			        SwaggerUIBundle.presets.apis,
			        SwaggerUIBundle.SwaggerUIStandalonePreset
			      ],
			      plugins: [
			        SwaggerUIBundle.plugins.DownloadUrl
			      ],
			    });
			</script>
			
			</html>
			""";
	}
	
	@SneakyThrows
	public static String convertToSpec(OpenAPI swagger) {
		return Json.pretty(swagger);
	}
	
}