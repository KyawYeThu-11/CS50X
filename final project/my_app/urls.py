from django.urls import path
from django.urls import path
from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("read_article/<str:article_id>", views.read_article, name="read_article"),
    path("request_articles/<int:category_id>", views.request_articles, name="request_articles"),
    path("request_category", views.request_category, name="request_category"),
    path("request_category/<int:category_id>", views.request_category, name="request_category"),
    path("request_gallery", views.request_gallery, name="request_gallery")
]
