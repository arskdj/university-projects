from django.shortcuts import render
from django.http import HttpResponse
from django.views import generic
from library.models import Book, BookInstance, Loan, Reservation
from django.views.generic.list import ListView
from django.views.generic.detail import DetailView
import operator
from django.db.models import Q
from django.contrib.auth.mixins import LoginRequiredMixin
from django.utils import timezone

# Create your views here.
def index(request):
    return HttpResponse('test')

class BookListView(ListView):
    model = Book
    paginate_by = 10

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['books'] = Book.objects.all()
        return context

class BookDetailView(DetailView):
    model = Book

class BookSearchListView(BookListView):
    paginate_by = 10

    def get_context_data(self, **kwargs):
        context = super(BookSearchListView, self).get_context_data(**kwargs)

        query = self.request.GET.get('q')
        if query:
            query_list = query.split()
            context['books'] = context['books'].filter(Q(title__contains=query) |Q(author__contains=query) |Q(isbn__contains=query))

        return context

class UserProfile(LoginRequiredMixin,ListView):
    model = BookInstance
    paginate_by = 10
    template_name = 'library/userprofile.html'

    def get_context_data(self, **kwargs):
        context = super(UserProfile, self).get_context_data(**kwargs)
        
        #create reservation
        res_isbn = self.request.GET.get('isbn')
        if res_isbn:
            reserv = Reservation(active=True,user=self.request.user,book=Book.objects.filter(isbn=res_isbn)[0],date_created=timezone.now())
            reserv.save()


        context['reservations'] = Reservation.objects.filter(user=self.request.user)
        context['loans'] = Loan.objects.filter(user=self.request.user)
        return context

class Statistics(ListView):
    model = Book
    paginate_by = 10
    template_name = 'library/statistics.html'

    def get_context_data(self, **kwargs):
        context = super(Statistics, self).get_context_data(**kwargs)

        books = Book.objects.all() 
        counts = []
        for b in books:
            c = b.reservation_set.count()
            counts.append((b,c))
        counts.sort(reverse=True,key=lambda tup: tup[1])
        context['counts'] = counts
        return context
