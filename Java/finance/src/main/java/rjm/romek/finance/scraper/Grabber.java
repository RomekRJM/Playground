package rjm.romek.finance.scraper;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonSubTypes;
import com.fasterxml.jackson.annotation.JsonSubTypes.Type;
import com.fasterxml.jackson.annotation.JsonTypeInfo;
import com.fasterxml.jackson.annotation.JsonTypeInfo.Id;
import java.util.SortedMap;
import javax.money.MonetaryAmount;
import java.io.IOException;
import java.util.Date;

@JsonTypeInfo(use = Id.NAME, property = "type")
@JsonSubTypes({
    @Type(value = GoogleGrabber.class, name = "GoogleGrabber")
})
public abstract class Grabber {

  @JsonProperty
  protected final String asset;

  protected Grabber() {
    this.asset = "";
  }

  protected Grabber(String asset) {
    this.asset = asset;
  }

  public abstract SortedMap<Date, MonetaryAmount> grabPrice()
      throws IOException, CouldNotGrabPriceException;

  public abstract String getUrl() throws IOException;
}
