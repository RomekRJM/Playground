package rjm.romek.finance.scheduler;

import java.io.IOException;
import java.util.Collection;
import lombok.AllArgsConstructor;
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
public class AdvisorScheduler implements ApplicationListener<ApplicationReadyEvent> {

  private final Deserializer deserializer;
  private final ThreadPoolTaskScheduler taskScheduler;

  // https://www.baeldung.com/spring-task-scheduler
  // todo: fix error handling, gracefully shut down with error codes
  @Override
  public void onApplicationEvent(ApplicationReadyEvent event) {
    Collection<Advisor> tasks = null;
    try {
      tasks = deserializer.load();
    } catch (IOException e) {
      e.printStackTrace();
    }

    assert tasks != null;

    tasks.forEach((t) -> {
      taskScheduler.schedule(() -> {
        try {
          t.check();
        } catch (IOException e) {
          e.printStackTrace();
        } catch (CouldNotGrabPriceException e) {
          e.printStackTrace();
        }
      }, new CronTrigger(t.getCron()));
      new AdvisorRunner(t);
    });
  }
}
