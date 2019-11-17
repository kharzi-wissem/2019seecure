from flask import render_template, flash, redirect, url_for, request
from flask_login import login_user, logout_user, current_user, login_required
from werkzeug.urls import url_parse
from app import app, db, r, q
from app.forms import LoginForm, RegistrationForm
from app.models import User
from flask import jsonify
import json

from rq.job import Job

import serial
from time import sleep

from app.tasks import count_words
from time import strftime


@app.route("/add-task", methods=["GET", "POST"])
def add_task():
    a=True
    while(a):
        jobs = q.jobs  # Get a list of jobs in the queue
        message = None
        a= 1
        task = q.enqueue(count_words, a)  # Send a job to the task queue
        jobs = q.jobs  # Get a list of jobs in the queue
        q_len = len(q)  # Get the queue length
        sleep(4)
        if task.result == "val":
            sleep(1)
            redirect(url_for('phish'))

    return render_template("add_task.html", message=message, jobs=jobs)


@app.route('/')
@app.route('/index', methods=['GET', 'POST'])
@login_required
def index():
    posts = [
        {
            'author': {'username': 'John'},
            'body': 'Beautiful day in Portland!'
        },
        {
            'author': {'username': 'Susan'},
            'body': 'The Avengers movie was so cool!'
        }
    ]
    if request.method=='POST':
        return 0
    return render_template('index.html', title='Home', posts=posts)


@app.route('/login', methods=['GET', 'POST'])
def login():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    form = LoginForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=form.username.data).first()

        if user is None or not user.check_password(form.password.data):
            flash('Invalid username or password')
            return redirect(url_for('login'))
        login_user(user, remember=form.remember_me.data)
        next_page = request.args.get('next')
        if not next_page or url_parse(next_page).netloc != '':
            next_page = url_for('index')
        return redirect(next_page)
    return render_template('login.html', title='Sign In', form=form)


@app.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('index'))

@app.route('/hacker')
def hacker():
    return render_template('hacker.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    form = RegistrationForm()
    if form.validate_on_submit():
        user = User(username=form.username.data, email=form.email.data)
        user.set_password(form.password.data)
        db.session.add(user)
        db.session.commit()
        flash('Congratulations, you are now a registered user!')
        return redirect(url_for('login'))
    return render_template('register.html', title='Register', form=form)

@app.route('/background_process_test',methods=['POST','GET'])
def background_process_test():
    if request.method=='POST':
        password = request.form['password']
        #ser = serial.Serial("/dev/ttyUSB0",9600)
        sleep(5)
        #ser.write(bytes('2','utf-8'))
        print("HELLO",password)
        json.dumps({"password":password})
    return json.dumps({"password":password})

@login_required
@app.route('/ransomware',methods=['POST','GET'])
def ransomware():
    return render_template('ransomware.html')

@login_required
@app.route('/phish',methods=['POST','GET'])
def phish():
    if request.method =='POST':
        a=True
        while(a):
            jobs = q.jobs  # Get a list of jobs in the queue
            message = None
            a= 1
            task = q.enqueue(count_words, a)  # Send a job to the task queue
            jobs = q.jobs  # Get a list of jobs in the queue
            q_len = len(q)  # Get the queue length
            sleep(4)
            if task.result == "val":
                sleep(1)
                redirect(url_for('ransomware'))
    else:
        print('0')
    return render_template('phish.html')

@app.route('/main',methods=['POST','GET'])
def main():
    if request.method=='POST':
        return redirect(url_for('login'))
    else:
        return render_template('firstpage.html')
