package rjm.romek.finance.scheduler;

import java.io.IOException;
import java.util.Collection;
import lombok.AllArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.context.event.ApplicationReadyEvent;
import org.springframework.context.ApplicationListener;
import org.springframework.scheduling.concurrent.ThreadPoolTaskScheduler;
import org.springframework.scheduling.support.CronTrigger;
import org.springframework.stereotype.Service;
import rjm.romek.finance.advisor.Advisor;
import rjm.romek.finance.advisor.Deserializer;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;

@Service
@AllArgsConstructor
@Slf4j
public class AdvisorScheduler implements ApplicationListener<ApplicationReadyEvent> {

  private final Deserializer deserializer;
  private final ThreadPoolTaskScheduler taskScheduler;

  // https://www.baeldung.com/spring-task-scheduler
  @Override
  public void onApplicationEvent(ApplicationReadyEvent event) {
    Collection<Advisor> tasks;
    try {
      tasks = deserializer.load();
    } catch (IOException e) {
      log.error("Could not read advisor definition file: %s", e.getMessage());
      return;
    }

    tasks.forEach((t) -> {
      taskScheduler.schedule(() -> {
        try {
          t.check();
        } catch (IOException e) {
          log.error("There was a problem while running the scheduler %s: %s", t.getName(),
              e.getMessage());
        } catch (CouldNotGrabPriceException e) {
          log.error("Problem while grabbing the price.", e);
        }
      }, new CronTrigger(t.getCron()));
      new AdvisorRunner(t);
    });
  }
}
