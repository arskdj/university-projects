from django.urls import path
from library.views import BookListView, BookDetailView, BookSearchListView, UserProfile, Statistics

urlpatterns = [
    path('', BookListView.as_view(), name='index'),
    path('book/<pk>', BookDetailView.as_view(), name='book_detail'),
    path('search/', BookSearchListView.as_view(), name='search_list'),
    path('userprofile/', UserProfile.as_view(), name='userprofile'),
    path('statistics/', Statistics.as_view(), name='statistics'),
]
