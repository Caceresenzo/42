package ft.framework.schedule;

import java.lang.reflect.Method;
import java.time.Duration;
import java.util.concurrent.TimeUnit;

import org.apache.commons.lang3.reflect.MethodUtils;

import ft.framework.schedule.annotation.Scheduled;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;

@RequiredArgsConstructor
public class ScheduledFactory {
	
	private final TaskScheduler taskScheduler;
	
	public <T> T scan(T object) {
		final var methods = MethodUtils.getMethodsWithAnnotation(object.getClass(), Scheduled.class);
		
		for (final var method : methods) {
			MethodUtils.getAccessibleMethod(method);
			
			for (final var annotation : method.getAnnotationsByType(Scheduled.class)) {
				schedule(object, method, annotation);
			}
		}
		
		return object;
	}
	
	public boolean schedule(Object object, Method method, Scheduled scheduled) {
		final var runner = new MethodRunner(object, method);
		
		final var cron = scheduled.cron();
		if (!Scheduled.CRON_DISABLED.equals(cron)) {
			taskScheduler.scheduleCron(runner, cron);
			return true;
		}
		
		final var fixedDelay = scheduled.fixedDelay();
		if (fixedDelay != 0) {
			final var timeUnit = scheduled.timeUnit();
			final var delay = toDuration(fixedDelay, timeUnit);
			
			final var initialDelay = scheduled.initialDelay();
			if (initialDelay != 0) {
				final var initial = toDuration(initialDelay, timeUnit);
				taskScheduler.scheduleFixedDelay(runner, delay, initial);
			} else {
				taskScheduler.scheduleFixedDelay(runner, delay);
			}
			
			return true;
		}
		
		return false;
	}
	
	public Duration toDuration(long value, TimeUnit timeUnit) {
		return Duration.ofMillis(timeUnit.toMillis(value));
	}
	
	public static class MethodRunner implements Runnable {
		
		private final Object object;
		private final Method method;
		
		public MethodRunner(Object object, Method method) {
			this.object = object;
			this.method = method;
			
			if (method.getParameterCount() != 0) {
				throw new IllegalArgumentException("method " + method + " must have zero parameter");
			}
		}
		
		@SneakyThrows
		@Override
		public void run() {
			method.invoke(object);
		}
		
	}
	
}