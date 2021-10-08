from django.http.response import JsonResponse
from django.shortcuts import render
# from markdown2 import Markdown
from django.core.files.storage import default_storage

from .models import Image, Text, Statistic, Blog_Category, Carousel, Contact, FAQ, FooterDoc, Article, Gallery
# Create your views here.
def index(request):
    # Image
    logo = Image.objects.get(identity = "Logo")
    heading = Image.objects.get(identity="Heading")
    one = Image.objects.get(identity="One")
    two = Image.objects.get(identity="Two")


    # Text
    sub_title = Text.objects.get(identity="Sub_Title")
    one_text = Text.objects.get(identity = "One")
    oneA_text = Text.objects.get(identity = "One-A")
    oneB_text = Text.objects.get(identity = "One-B")
    two_text = Text.objects.get(identity = "Two")
    three_text = Text.objects.get(identity = "Three")
    four_text = Text.objects.get(identity = "Four")
    button = Text.objects.get(identity = "Button")


    # Statistics, Blog_Category, Carousels, Contact, FAQ, FooterDoc
    statistics = Statistic.objects.all()
    blog_categories = Blog_Category.objects.all()
    slides = Carousel.objects.all()
    contacts = Contact.objects.all()
    faq = FAQ.objects.all()
    documents = FooterDoc.objects.all()

    return render(request, "my_app/index.html", {
        "logo":logo,
        "heading":heading,
        "sub_title":sub_title,
        "one":one,
        "two":two,
        "one_text":one_text,
        "oneA_text":oneA_text,
        "oneB_text":oneB_text,
        "two_text":two_text,
        "three_text":three_text,
        "four_text":four_text,
        "button":button,
        "statistics":statistics, 
        "blog_categories":blog_categories,
        "slides":slides,
        "contacts":contacts,
        "faq":faq,
        "documents":documents
    })

def read_article(_, article_id):
    article = Article.objects.get(id = article_id)

    dictionary = {
        "title":article.title,
        "image":article.image,
        "content":article.article,
        "category":article.category.title,
        "color":article.category.color,
        "timestamp":article.timestamp
    }
    return JsonResponse(dictionary, safe=False)

def request_articles(_, category_id):
    articles = Article.objects.filter(category__id = category_id).order_by("-timestamp").all()
    return JsonResponse([article.serialize() for article in articles], safe=False)

def request_category(_, category_id=None):
    if not category_id:
        categories = Blog_Category.objects.all()
        return JsonResponse([category.serialize() for category in categories], safe=False)
    else:
        category = Blog_Category.objects.get(id=category_id)
    return JsonResponse(category.serialize(), safe=False)

def request_gallery(_):
    images = Gallery.objects.all().order_by("-timestamp")
    return JsonResponse([image.serialize() for image in images], safe=False)

    # markdowner = Markdown()
    # url = article.article
    # file = open(url)
    # decoded_file = file.read().decode("utf-8")
    # content = markdowner.convert(decoded_file)