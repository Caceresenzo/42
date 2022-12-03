package ft.app.matcha.controller;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.RestController;
import ft.framework.util.MediaTypes;

@RestController(path = "/pictures", produce = MediaTypes.PNG)
public class PictureController {
	
	@GetMapping
	public InputStream index() throws FileNotFoundException {
		return new FileInputStream("buse.png");
	}
	
}