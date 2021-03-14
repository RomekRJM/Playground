package rjm.romek.finance;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.util.ResourceUtils;
import rjm.romek.finance.notifier.EmailNotifier;

class DeserializerTest {
  private final Deserializer deserializer = new Deserializer();

  private File testFile;

  @BeforeEach
  public void setUp() throws FileNotFoundException {
    testFile = ResourceUtils.getFile("classpath:test-jobs.yaml");
  }

  @Test
  public void shouldDeserialize() throws IOException {
    Collection<Advisor> loaded = deserializer.load(testFile);

    assertEquals(1, loaded.size());
  }

  @Test
  public void shouldSerialize() throws IOException {
    Advisor advisor = new Advisor(new EmailNotifier(), "abcd");
    Collection<Advisor> advisors = Collections.singletonList(advisor);
    File tmpFile = File.createTempFile("asd", "yaml");
    deserializer.save(advisors, tmpFile);
  }
}