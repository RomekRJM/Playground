package rjm.romek.finance.scheduler;

import java.io.IOException;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import rjm.romek.finance.advisor.Advisor;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;

@Slf4j
@RequiredArgsConstructor
public class AdvisorRunner implements Runnable {

  private final Advisor advisor;

  @Override
  public void run() {
    try {
      advisor.check();
    } catch (IOException | CouldNotGrabPriceException e) {
      log.error("There was a problem running advisor %s. Error: %s", advisor.getName(),
          e.getMessage());
    }
  }
}
