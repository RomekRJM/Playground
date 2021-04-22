package rjm.romek.finance.scheduler;

import java.io.IOException;
import lombok.extern.slf4j.Slf4j;
import rjm.romek.finance.advisor.Advisor;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;

@Slf4j
public class AdvisorRunner extends Thread {

  private final Advisor advisor;

  public AdvisorRunner(final Advisor advisor) {
    super(advisor == null ? "AdvisorThread" : advisor.getName());
    this.advisor = advisor;
  }

  @Override
  public void run() {
    log.info("Starting the advisor: {}", advisor.getName());

    try {
      advisor.check();
    } catch (IOException e) {
      log.error("There was a problem while running the scheduler {}: {}", advisor.getName(),
          e.getMessage());
    } catch (CouldNotGrabPriceException e) {
      log.error("Problem while grabbing the price.", e);
    }
  }

}
