package rjm.romek.finance.notifier.model;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface NotificationRepository extends JpaRepository<Notification, Long> {

  Notification findTopByAdvisorNameEqualsAndAndRecipientEqualsOrderByDateDesc(
      String advisorName, String recipient);
}
