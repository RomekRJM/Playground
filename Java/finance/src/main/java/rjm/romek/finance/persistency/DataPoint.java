package rjm.romek.finance.persistency;

import java.util.Date;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Index;
import javax.persistence.Table;
import lombok.Data;

@Data
@Entity
@Table(
    name = "DATA_POINT",
    indexes = {
        @Index(name = "date_advisor_index", columnList = "date, advisorName")
    }
)
public class DataPoint {

  @Id
  @GeneratedValue
  private Long Id;

  private Date date;

  private String advisorName;

  private String currencyCode;

  private Number value;
}
