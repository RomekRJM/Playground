package rjm.romek.finance.notifier;

import javax.validation.constraints.Max;
import javax.validation.constraints.Min;
import javax.validation.constraints.NotBlank;
import lombok.Getter;
import lombok.Setter;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.validation.annotation.Validated;

@Validated
@ConfigurationProperties(prefix="smtp")
@Getter
@Setter
public class SmtpProperties {

  @NotBlank
  private String host;

  @Min(1)
  @Max(65535)
  private String port;

  @NotBlank
  private String user;

  @NotBlank
  private String password;

}
