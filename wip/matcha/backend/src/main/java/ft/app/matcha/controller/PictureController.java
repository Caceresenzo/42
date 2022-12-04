package ft.app.matcha.controller;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.Controller;
import ft.framework.util.MediaTypes;

@Controller
@RequestMapping(path = "/pictures")
public class PictureController {
	
	@GetMapping(produce = MediaTypes.PNG)
	public InputStream index() throws FileNotFoundException {
		return new FileInputStream("buse.png");
	}
	
}