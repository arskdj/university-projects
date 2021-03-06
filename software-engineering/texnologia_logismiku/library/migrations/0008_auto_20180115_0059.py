# Generated by Django 2.0 on 2018-01-14 22:59

import datetime
from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion
from django.utils.timezone import utc


class Migration(migrations.Migration):

    dependencies = [
        ('library', '0007_auto_20180115_0055'),
    ]

    operations = [
        migrations.AlterField(
            model_name='loan',
            name='start_date',
            field=models.DateField(blank=True, default=datetime.datetime(2018, 1, 14, 22, 59, 28, 658394, tzinfo=utc), null=True),
        ),
        migrations.AlterField(
            model_name='loan',
            name='user',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.CASCADE, to=settings.AUTH_USER_MODEL),
        ),
        migrations.AlterField(
            model_name='reservation',
            name='date_created',
            field=models.DateField(blank=True, default=datetime.datetime(2018, 1, 14, 22, 59, 28, 657681, tzinfo=utc), null=True),
        ),
    ]
