package rjm.romek.finance;

import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@Slf4j
public class FinanceApplication implements CommandLineRunner {

  public static void main(String[] args) {
    SpringApplication.run(FinanceApplication.class, args);

    log.info("Use SIGKILL to stop the app.");
  }

  @Override
  public void run(String... args) {

  }
}
