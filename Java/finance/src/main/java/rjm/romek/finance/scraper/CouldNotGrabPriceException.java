package rjm.romek.finance.scraper;

public class CouldNotGrabPriceException extends Exception {
  public CouldNotGrabPriceException() {
    super("There was a problem grabbing the value.");
  }

  public CouldNotGrabPriceException(Exception exception) {
    super("There was a problem grabbing the value.", exception);
  }

  public CouldNotGrabPriceException(String problem) {
    super("There was a problem grabbing the value: " + problem);
  }
}
