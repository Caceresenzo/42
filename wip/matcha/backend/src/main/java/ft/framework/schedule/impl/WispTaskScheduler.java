package ft.framework.schedule.impl;

import java.time.Duration;

import com.coreoz.wisp.Scheduler;
import com.coreoz.wisp.schedule.Schedules;
import com.coreoz.wisp.schedule.cron.CronExpressionSchedule;

import ft.framework.schedule.TaskScheduler;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class WispTaskScheduler implements TaskScheduler {
	
	private final Scheduler scheduler;
	
	public WispTaskScheduler() {
		this(new Scheduler());
	}
	
	@Override
	public void scheduleCron(Runnable runnable, String cron) {
		final var schedule = CronExpressionSchedule.parseWithSeconds(cron);
		
		scheduler.schedule(runnable, schedule);
	}
	
	@Override
	public void scheduleFixedDelay(Runnable runnable, Duration delay) {
		final var schedule = Schedules.fixedDelaySchedule(delay);
		
		scheduler.schedule(runnable, schedule);
	}
	
	@Override
	public void scheduleFixedDelay(Runnable runnable, Duration delay, Duration initialDelay) {
		final var schedule = Schedules.afterInitialDelay(Schedules.fixedDelaySchedule(delay), initialDelay);
		
		scheduler.schedule(runnable, schedule);
	}
	
}