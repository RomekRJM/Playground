package rjm.romek.finance.persistency;

import java.util.Date;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Index;
import javax.persistence.Table;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Builder
@AllArgsConstructor
@NoArgsConstructor
@Data
@Entity
@Table(
    indexes = {
        @Index(name = "date_advisor_index", columnList = "date, advisorName")
    }
)
public class DataPoint implements Comparable<DataPoint> {

  @Id
  @GeneratedValue
  private Long Id;

  private Date date;

  private String advisorName;

  private String currencyCode;

  private Double value;

  @Override
  public int compareTo(DataPoint other) {
    return this.getDate().compareTo(other.getDate());
  }
}
