async def main():
    dialogs = await tg.get_dialogs()
    for dialog in dialogs:
        entity = dialog.entity
        messages = await tg.get_messages(entity, limit=1)
        print(f"Диалог: {dialog.title or dialog.name}, сообщений: {messages.total}")