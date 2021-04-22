package rjm.romek.finance.notifier.model;

import java.util.Date;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@AllArgsConstructor
@NoArgsConstructor
@Builder
@Entity
@Data
public class Notification {
  @Id
  @GeneratedValue
  private Long Id;

  private Date date;

  private String advisorName;

  private String recipient;
}
