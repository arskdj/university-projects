from django.core.management.base import BaseCommand, CommandError
from library.models import Loan
from django.core.mail import send_mail


class Command(BaseCommand):
    help = 'Send email notification for due loans'

#    def add_arguments(self, parser):
#        parser.add_argument('poll_id', nargs='+', type=int)

    def handle(self, *args, **options):
        loans = Loan.objects.get_past_due_loans()
        print(loans)
        emails = [l.user.email for l in loans]
        send_mail( 'Βιβλιοθήκη Σάμου - Επιστροφή Βιβλίου',
                'Έχει περάσει η ημερομηνία επιστροφής.',
                recipient_list=[emails],
                from_email = "library@samos.gr",
                fail_silently=False,)
        self.stdout.write(self.style.SUCCESS("Emails sent"))
