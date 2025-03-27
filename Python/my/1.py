from bs4 import BeautifulSoup
import re
from collections import Counter
from datetime import datetime

# Paths to the uploaded files
file_paths = [
    "messages.html",
    "messages2.html",
    "messages3.html",
    "messages4.html",
    "messages5.html",
    "messages6.html",
    "messages7.html",
    "messages8.html",
    "messages9.html",
    "messages10.html",
    "messages11.html",
    "messages12.html",
    "messages13.html",
    "messages14.html",
    "messages15.html",
    "messages16.html",
    "messages17.html",
    "messages18.html",

]


# Helper function to extract messages
def extract_messages(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        soup = BeautifulSoup(file, 'html.parser')

    messages = []
    for message in soup.find_all('div', class_='message default clearfix'):
        user = message.find('div', class_='from_name')
        text = message.find('div', class_='text')
        date = message.find('div', class_='pull_right date details')

        if user and text and date:
            messages.append({
                'user': user.text.strip(),
                'text': text.text.strip(),
                'datetime': datetime.strptime(date['title'], "%d.%m.%Y %H:%M:%S UTC%z")
            })
    return messages


# Extract messages from all files
all_messages = []
for file_path in file_paths:
    all_messages.extend(extract_messages(file_path))

# Statistics calculation
total_messages = len(all_messages)
messages_by_user = Counter([msg['user'] for msg in all_messages])
times = [msg['datetime'].time() for msg in all_messages]
most_active_time = Counter([t.hour for t in times]).most_common(1)[0]

print(total_messages, messages_by_user, most_active_time)