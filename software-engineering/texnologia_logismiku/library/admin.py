from django.contrib import admin

# Register your models here.
from .models import Book, BookInstance, Reservation, Loan

admin.site.register(Book)
admin.site.register(BookInstance)
admin.site.register(Reservation)
admin.site.register(Loan)
