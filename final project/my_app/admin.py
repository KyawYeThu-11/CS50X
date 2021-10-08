from django.contrib import admin
from .models import Image, Text, Statistic, Blog_Category, Carousel, Article, Gallery, Contact, FAQ, FooterDoc

class ImageAdmin(admin.ModelAdmin):
    list_display = ("identity", "name", "description")

class TextAdmin(admin.ModelAdmin):
    list_display = ("identity", "name", "text")

class StatisticAdmin(admin.ModelAdmin):
    list_display = ("unit", "number")

class Blog_CategoryAdmin(admin.ModelAdmin):
    list_display = ("id", "title", "text")

class CarousleAdmin(admin.ModelAdmin):
    list_display = ("id", "link")

class ContactAdmin(admin.ModelAdmin):
    list_display = ("id", "media", "URL", "username", "phone_number")

class FAQAdmin(admin.ModelAdmin):
    list_display = ("id", "question", "answer")

class FooterDocAdmin(admin.ModelAdmin):
    list_display = ("id", "document_title", "text")

class ArticleAdmin(admin.ModelAdmin):
    list_display = ("id", "title", "timestamp")

class GalleryAdmin(admin.ModelAdmin):
    list_display = ("id", "name", "category", "timestamp")


# Register your models here.
admin.site.register(Image, ImageAdmin)
admin.site.register(Text, TextAdmin)
admin.site.register(Statistic, StatisticAdmin)
admin.site.register(Blog_Category, Blog_CategoryAdmin)
admin.site.register(Carousel, CarousleAdmin)
admin.site.register(Contact, ContactAdmin)
admin.site.register(FAQ, FAQAdmin)
admin.site.register(FooterDoc, FooterDocAdmin)
admin.site.register(Article, ArticleAdmin)
admin.site.register(Gallery, GalleryAdmin)