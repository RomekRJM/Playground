package rjm.romek.finance.scheduler;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.doThrow;
import static org.mockito.Mockito.when;

import java.io.IOException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.springframework.boot.test.system.CapturedOutput;
import org.springframework.boot.test.system.OutputCaptureExtension;
import rjm.romek.finance.advisor.Advisor;
import rjm.romek.finance.scraper.CouldNotGrabPriceException;

@ExtendWith(OutputCaptureExtension.class)
class AdvisorRunnerTest {

  @Mock
  private Advisor advisor;

  private AdvisorRunner runner;

  @BeforeEach
  public void setUp() {
    MockitoAnnotations.openMocks(this);
    when(advisor.getName()).thenReturn("abcd");
    runner = new AdvisorRunner(advisor);
  }

  @Test
  public void shouldRun(CapturedOutput output) {
    runner.run();
    assertTrue(output.getOut().contains("Starting the advisor: abcd"));
  }

  @Test
  public void shouldLogIOException(CapturedOutput output) throws CouldNotGrabPriceException, IOException {
    doThrow(IOException.class).when(advisor).check();
    runner.run();
    assertTrue(output.getOut().contains("There was a problem while running the scheduler"));
  }

  @Test
  public void shouldLogCouldNotGrabPriceException(CapturedOutput output) throws CouldNotGrabPriceException, IOException {
    doThrow(CouldNotGrabPriceException.class).when(advisor).check();
    runner.run();
    assertTrue(output.getOut().contains("Problem while grabbing the price."));
  }
}