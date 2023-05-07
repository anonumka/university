const express = require('express')
const bodyParser = require('body-parser')
const mustache = require('mustache')
const fs = require('fs')

const app = express()

const host = 'localhost'
const port = 3000

const urlencodedParser = express.urlencoded({extended: false});

app.use(bodyParser.json())
app.use(express.static(process.cwd() + '/public'))

app.get('/', (req, res) => {
    res.sendFile(process.cwd() + '/public/index.html')
})

app.get('/main', (req, res) => {
    const data = JSON.parse(fs.readFileSync('public/main.json'));
    const file = fs.readFileSync('public/template.html', 'utf-8');
    const template = mustache.render(file, data);
    
    res.send(template);
})

app.get('/forum', (req, res) => {
    const data = JSON.parse(fs.readFileSync('public/forum.json'));
    const file = fs.readFileSync('public/template.html', 'utf-8').toString();
    const template = mustache.render(file, data);
    
    res.send(template);
})

app.get('/contacts', (req, res) => {
    const data = JSON.parse(fs.readFileSync('public/contacts.json'));
    const file = fs.readFileSync('public/template.html', 'utf-8').toString();
    const template = mustache.render(file, data);
    
    res.send(template);
})

app.get('/about', (req, res) => {
    const data = JSON.parse(fs.readFileSync('public/about.json'));
    const file = fs.readFileSync('public/template.html', 'utf-8').toString();
    const template = mustache.render(file, data);
    
    res.send(template);
})

app.get('/feedback', (req, res) => {
    const data = JSON.parse(fs.readFileSync('public/feedback.json'));
    const file = fs.readFileSync('public/template.html', 'utf-8').toString();
    const template = mustache.render(file, data);
    
    res.send(template);
})

app.post('/jobApplication', urlencodedParser, (req, res) => {
    const defaultInput = req.body.inputUser
    const defaultCheck = req.body.checkboxUser
    const defaultRadio = req.body.radioUser
  
    res.send(defaultInput, defaultCheck, defaultRadio)
    console.log(defaultInput, defaultCheck, defaultRadio)
})

app.listen(port, host, () =>
{
    console.log(`Сайт готов к работе. Доступен по адресу http://${host}:${port}`);
});