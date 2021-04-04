package rjm.romek.finance;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Collection;
import java.util.Collections;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import rjm.romek.finance.advisor.Advisor;
import rjm.romek.finance.advisor.Deserializer;
import rjm.romek.finance.alert.Alert;
import rjm.romek.finance.notifier.EmailNotifier;
import rjm.romek.finance.rule.PriceAboveRule;
import rjm.romek.finance.scraper.GoogleGrabber;

class DeserializerTest {

  private final Deserializer deserializer = new Deserializer();

  private String testFileName;

  @BeforeEach
  public void setUp() {
    testFileName = "test-jobs.yaml";
  }

  @Test
  public void shouldDeserialize() throws IOException {
    Collection<Advisor> loaded = deserializer.load(testFileName);

    assertEquals(1, loaded.size());
  }

  @Test
  public void shouldSerialize() throws IOException {
    Advisor advisor = new Advisor(
        new EmailNotifier().withEmail("wawel@o2.pl"),
        new GoogleGrabber("google+share+price"),
        "abcd",
        new Alert(new PriceAboveRule(MonetaryUtil.getDollars(1300)), 3),
        "0 0 0 * * *"
    );
    Collection<Advisor> advisors = Collections.singletonList(advisor);
    File tmpFile = File.createTempFile("asd", "yaml");
    deserializer.save(advisors, tmpFile);
    return;
  }
}