from django.db import models
from django.db.models.fields.files import ImageField
from multiselectfield import MultiSelectField

# Create your models here.
class Image(models.Model):
    identity = models.CharField(max_length=32)
    name = models.CharField(max_length=64)
    image = models.URLField()
    description = models.TextField(null=True, blank=True)

    def __str__(self):
        return f"{self.identity} {self.name} {self.image} {self.description}"

class Text(models.Model):
    identity = models.CharField(max_length=32, unique=True)
    name = models.CharField(max_length=64)
    text = models.TextField()

    def __str__(self):
        return f"{self.identity} {self.name} {self.text}"

class Statistic(models.Model):
    icon = models.URLField()
    number = models.CharField(max_length=32)
    unit = models.CharField(max_length=64)

    def __str__(self):
        return f"{self.icon} {self.number} {self.unit}"

class Blog_Category(models.Model):
    colors = (
        ('primary', 'blue'),
        ('secondary', 'grey'),
        ('success', 'green'),
        ('danger', 'red'),
        ('warning text-dark', 'orange'),
        ('info text-dark', 'light blue'),
        ('dark', 'black'),
        )
    title = models.CharField(max_length=32)
    text = models.TextField()
    image = models.URLField()
    color = MultiSelectField(choices=colors, max_choices=1)

    def serialize(self):
        return {
            "id":self.id,
            "title": self.title,
            "image":self.image,
            "text": self.text
        }

    def __str__(self):
        return f"{self.title}"

class Carousel(models.Model):
    link = models.URLField()

    def __str__(self):
        return f"{self.id} {self.link}"

class Contact(models.Model):
    media = models.CharField(max_length=32)
    URL = models.URLField(blank=True)
    username = models.CharField(max_length=64, blank=True)
    phone_number = models.CharField(max_length=32, blank=True)

    def __str__(self):
        return f"{self.media} {self.username} {self.phone_number}"

class FAQ(models.Model):
    question = models.TextField()
    answer = models.TextField()

    def __str__(self):
        return f"{self.question}{self.answer}"

class FooterDoc(models.Model):
    document_title = models.CharField(max_length=32)
    text = models.TextField()

    def __str__(self):
        return f"{self.document_title} {self.text}"

class Article(models.Model):
    title = models.CharField(max_length=64)
    image = models.URLField()
    article = models.TextField()
    category = models.ForeignKey(Blog_Category, on_delete=models.PROTECT)
    timestamp = models.DateField(auto_now=True)

    def serialize(self):
        return {
            "id":self.id,
            "title":self.title,
            "image":self.image,
            "article": self.article,
            "category": self.category.title,
            "category_color": self.category.color,
        }

    def __str__(self):
        return f"{self.id} {self.title}"

class Gallery(models.Model):
    name = models.CharField(max_length=64)
    image = models.URLField()
    category = models.CharField(max_length=64)
    timestamp = models.DateField(auto_now=True)

    def serialize(self):
        return {
            "id":self.id,
            "name":self.name,
            "image":self.image,
            "category": self.category,
            "timestamp":self.timestamp
        }

    def __str__(self):
        return f"{self.id} {self.name}"
    