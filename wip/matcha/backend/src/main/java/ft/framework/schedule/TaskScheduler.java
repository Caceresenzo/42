package ft.framework.schedule;

import java.time.Duration;

public interface TaskScheduler {
	
	void scheduleCron(Runnable runnable, String cron);
	
	void scheduleFixedDelay(Runnable runnable, Duration delay);
	
	void scheduleFixedDelay(Runnable runnable, Duration delay, Duration initialDelay);
	
}