package rjm.romek.finance.notifier;

import lombok.Data;

@Data
public class Notification {
  private final String body;
  private final String subject;
}
