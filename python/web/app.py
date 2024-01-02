from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
import os
import yaml


basedir = os.path.abspath(os.path.dirname(__name__))
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + \
    os.path.join(basedir, 'blog.db')
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)


class Post(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(100))
    content = db.Column(db.Text)

    def __init__(self, title, content):
        self.title = title
        self.content = content


# @app.route('/home')
# def home():
#     posts = Post.query.all()
#     return render_template('home.html', posts=posts)


# @app.route('/create', methods=['GET', 'POST'])
# def create():
#     if request.method == 'POST':
#         title = request.form['title']
#         content = request.form['content']
#         post = Post(title, content)
#         db.session.add(post)
#         db.session.commit()
#         return redirect(url_for('home'))
#     return render_template('create.html')

@app.route('/search', methods=['GET', 'POST'])
def search():
    if request.method == 'POST':
        key = request.form['key']
    elif request.method == 'GET':
        key = request.args.get('key')
    else:
        key = None
    
    with open('data.yaml', 'r', encoding='utf8') as file:
        data = yaml.load(file, Loader=yaml.FullLoader)
    if key is None or key == '':
        return render_template('index.html', data=data)

    with open('search.yaml', 'r', encoding='utf8') as file:
        search = yaml.load(file, Loader=yaml.FullLoader)
        search['key'] = key
    return render_template('search.html', data=data, search=search)


@app.route('/', methods=['GET', 'POST'])
@app.route('/index/', methods=['GET', 'POST'])
def index():
    with open('data.yaml', 'r', encoding='utf8') as file:
        data = yaml.load(file, Loader=yaml.FullLoader)
    return render_template('index.html', data=data)


if __name__ == '__main__':
    app.run(debug=True)
