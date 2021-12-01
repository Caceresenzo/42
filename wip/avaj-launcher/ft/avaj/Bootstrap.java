package ft.avaj;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.nio.charset.StandardCharsets;

import ft.avaj.exception.NotEnoughArgumentException;
import ft.avaj.exception.TooMuchArgumentException;
import ft.avaj.simulation.Simulation;

public class Bootstrap {
	
	public static final boolean DEBUG = true;
	public static final String OUTPUT_FILE = "simulation.txt";
	
	public static void main(String[] args) {
		try {
			File scenarioFile = getScenarioFileFromArguments(args);
			
			Simulation simulation = Simulation.fromFile(scenarioFile);
			
			run(simulation);
		} catch (Exception exception) {
			/* Any error messages will be printed to the standard output. */
			
			System.out.print("could not run the simulation: ");
			System.out.println(exception.getClass().getName());
			System.out.println(exception.getMessage());
			
			if (DEBUG) {
				exception.printStackTrace();
			}
			
			System.exit(1);
		}
	}
	
	/* Your program will take one and only one argument from the command line. */
	private static File getScenarioFileFromArguments(String[] args) {
		int got = args.length;
		
		if (args.length < 1) {
			throw new NotEnoughArgumentException();
		}
		
		if (args.length > 1) {
			throw new TooMuchArgumentException(got);
		}
		
		return new File(args[0]);
	}
	
	private static void run(Simulation simulation) throws FileNotFoundException, UnsupportedEncodingException {
		PrintStream stdout = System.out;
		
		/* Executing the program will generate a file simulation.txt that describes the outcome of the simulation */
		FileOutputStream fileOutputStream = new FileOutputStream(OUTPUT_FILE);
		try (PrintStream printStream = new PrintStream(fileOutputStream, true, StandardCharsets.UTF_8.name())) {
			if (!DEBUG) {
				System.setOut(printStream);
			}
			
			simulation.run();
		} finally {
			System.setOut(stdout);
		}
	}
	
}