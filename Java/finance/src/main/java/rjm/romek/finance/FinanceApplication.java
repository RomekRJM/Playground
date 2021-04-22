package rjm.romek.finance;

import java.util.concurrent.CountDownLatch;
import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
@Slf4j
public class FinanceApplication {

  @Bean
  public CountDownLatch closeLatch() {
    return new CountDownLatch(1);
  }

  public static void main(String[] args) throws InterruptedException {
    ConfigurableApplicationContext ctx = SpringApplication.run(FinanceApplication.class, args);
    log.info("Use SIGKILL to stop the app.");

    final CountDownLatch closeLatch = ctx.getBean(CountDownLatch.class);
    Runtime.getRuntime().addShutdownHook(new Thread(() -> closeLatch.countDown()));
    closeLatch.await();
  }
}
