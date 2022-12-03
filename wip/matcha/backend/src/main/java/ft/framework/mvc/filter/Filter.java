package ft.framework.mvc.filter;

import spark.Request;
import spark.Response;

public interface Filter {
	
	default void preProcess(Request request, Response response) {
	};
	
	default void postProcess(Request request, Response response) {
	};
	
}