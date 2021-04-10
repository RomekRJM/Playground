package rjm.romek.finance.notifier;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import java.util.Date;
import java.util.Properties;
import javax.mail.Authenticator;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;

@Slf4j
@JsonDeserialize
@NoArgsConstructor
@AllArgsConstructor
@Getter
public class EmailNotifier {

  @Value("${smtp.emailTo}")
  private String email;

  @JsonIgnore
  @Value("${smtp.host}")
  private String smtpHost;

  @JsonIgnore
  @Value("${smtp.port}")
  private String smtpPort;

  @JsonIgnore
  @Value("${smtp.user}")
  private String smtpUser;

  @JsonIgnore
  @Value("${smtp.password}")
  private String smtpPassword;

  public void notify(Notification notification) {
    sendEmail(getSession(), email, notification.getSubject(), notification.getBody(), smtpUser);
  }

  private Session getSession() {
    Properties props = new Properties();
    props.put("mail.smtp.host", smtpHost);
    props.put("mail.smtp.port", smtpPort);
    props.put("mail.smtp.auth", "true");
    props.put("mail.smtp.starttls.enable", "true");
    props.put("mail.smtp.socketFactory.class", "javax.net.ssl.SSLSocketFactory");
    props.put("mail.smtp.connectiontimeout", "3000");
    props.put("mail.smtp.timeout", "5000");

    Authenticator auth = new Authenticator() {
      protected PasswordAuthentication getPasswordAuthentication() {
        return new PasswordAuthentication(smtpUser, smtpPassword);
      }
    };
    return Session.getInstance(props, auth);
  }

  private static void sendEmail(Session session, String email, String subject, String body,
      String from) {

    try {
      MimeMessage msg = new MimeMessage(session);
      msg.addHeader("Content-type", "text/HTML; charset=UTF-8");
      msg.addHeader("format", "flowed");
      msg.addHeader("Content-Transfer-Encoding", "8bit");

      msg.setFrom(new InternetAddress(from));
      msg.setReplyTo(InternetAddress.parse(from, false));
      msg.setSubject(subject, "UTF-8");
      msg.setText(body, "UTF-8");
      msg.setSentDate(new Date());

      msg.setRecipients(Message.RecipientType.TO, InternetAddress.parse(email, false));
      Transport.send(msg, msg.getAllRecipients());

    } catch (MessagingException e) {
      log.error("Can't send the email: " + e.getMessage());
    }
  }

}
