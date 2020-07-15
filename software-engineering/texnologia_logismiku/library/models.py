from django.db import models
from django.contrib.auth.models import User
from django.conf import settings
from django.utils import timezone
import uuid
from datetime import date, timedelta
from django.db.models import Q


class Book(models.Model):
    isbn = models.CharField(primary_key=True,max_length=13)
    title = models.CharField(max_length=200,null=True)
    author = models.CharField(max_length=200,null=True)

    def __str__(self):
        return self.title

class BookInstance(models.Model):
    id = models.UUIDField(primary_key=True, default = uuid.uuid4)
    book = models.ForeignKey('Book', on_delete = models.CASCADE, null=True, blank=True)

    STATUS = (
            ('m', 'Maintenance'),
            ('o', 'On loan'),
            ('a', 'Available'),
            ('r', 'Reserved'),
    )

    status = models.CharField(max_length=1, choices=STATUS, default='m', help_text='Book availability')

    def __str__(self):
        return '%s (%s)' % (self.id, self.book.title)


class Reservation(models.Model):
    active = models.BooleanField(default=True)
    user = models.ForeignKey(User, on_delete=models.CASCADE, null=True, blank=True)
    book = models.ForeignKey('Book', on_delete = models.CASCADE, null=True, blank=True)
    date_created = models.DateTimeField(null=True, blank=True, default=timezone.now())

    def __str__(self):
        return '%s - %s' % (self.user, self.book)


class LoanManager(models.Manager):
    def get_past_due_loans(self):
        return self.filter(Q(return_date__lte=timezone.now()) & Q(active=True))


class Loan(models.Model):
    def save(self, *args, **kwargs):
        if self.active == True:
            self.book_instance.status = 'o'
        else:
            self.book_instance.status = 'a'
        self.book_instance.save()
        super(Loan, self).save(args, kwargs)

    objects = LoanManager()
    active = models.BooleanField(default=True)
    user = models.ForeignKey(User, on_delete=models.CASCADE, null=True, blank=True)
    book_instance = models.ForeignKey('BookInstance', on_delete = models.CASCADE, null=True, blank=True, limit_choices_to={'status': 'a'})
    start_date = models.DateField(null=True, blank=True, default=date.today())
    return_date = models.DateField(null=True, blank=True, default=date.today()+timedelta(days=7))

    def __str__(self):
        if not self.active:
            msg = "[Done] "
        else:
            msg = "[Active] "
        return msg + self.user.username + " - " + str(self.book_instance.id)
