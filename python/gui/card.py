import tkinter as tk

class KnowledgeCardApp:
   def __init__(self):
       self.window = tk.Tk()
       self.window.title("知识卡片")

       self.text_box = tk.Text(self.window, wrap=tk.WORD, width=50, height=20)
       self.text_box.pack()

       self.submit_button = tk.Button(self.window, text="制作卡片", command=self.create_card)
       self.submit_button.pack()

   def create_card(self):
       # 获取文本框中的内容
       text = self.text_box.get("1.0", tk.END)

       # 创建一个新的卡片窗口
       card_window = tk.Toplevel(self.window)
       card_window.title("知识卡片")

       # 在新的窗口中显示文本内容
       card_text = tk.Text(card_window, wrap=tk.WORD, width=50, height=20)
       card_text.insert(tk.END, text)
       card_text.pack()

if __name__ == "__main__":
   app = KnowledgeCardApp()
   app.window.mainloop()