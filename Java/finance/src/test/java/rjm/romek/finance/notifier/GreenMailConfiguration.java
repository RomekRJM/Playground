package rjm.romek.finance.notifier;

import com.icegreen.greenmail.spring.GreenMailBean;
import org.springframework.boot.test.context.TestConfiguration;
import org.springframework.context.annotation.Bean;

@TestConfiguration
public class GreenMailConfiguration {

  @Bean
  public GreenMailBean greenMailBean() {
    GreenMailBean greenMailBean = new GreenMailBean();
    greenMailBean.setPortOffset(3000); // will receive emails on 3025
    return greenMailBean;
  }
}
