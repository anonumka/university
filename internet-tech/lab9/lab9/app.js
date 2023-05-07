const express = require('express')
const bodyParser = require('body-parser')
const mustache = require('mustache')
const fs = require('fs')
const { MongoClient } = require('mongodb');
var bson = require('bson');

// Connection URL
const url = 'mongodb://0.0.0.0:27017';
const client = new MongoClient(url);

// Database Name
const dbName = 'lab9';

const app = express()

const host = 'localhost'
const port = 3000

const urlencodedParser = express.urlencoded({extended: false});

app.use(bodyParser.json())
app.use(express.static(process.cwd() + '/public'))

/* Загрузка главной страницы */
app.get('/', (req, res) => {
	load_main_page(req, res)
})

async function load_main_page(req, res) {
	// Use connect method to connect to the server
	await client.connect();
	const db = client.db(dbName);
	const collection = db.collection('ads');

	let data = {
		title: "Главная страница",
		info: ""
	}
    const findResult = await collection.find({}).toArray();
	let info = '';
	for (let i = 0; i < findResult.length; i++)
	{	
		let tmp = '<div class="ad"><span class="title">';
		tmp = tmp + findResult[i].title + '</span>';
		
		tmp = tmp + '<span class="cost">';
		tmp = tmp + findResult[i].cost + ' ₽</span>';
		
		tmp = tmp + '<span class="description">';
		tmp = tmp + findResult[i].description + '</span>';

		tmp = tmp + '<button class="btn btn-primary btn-md" value="' + findResult[i]._id + '" type="submit"><img src="/img/trash.png"></button></div>'; 
		info = info + tmp;
	}
	
	data.info = info;
    const file = fs.readFileSync('public/template.html', 'utf-8');
    const template = mustache.render(file, data);
    
    res.send(template);
}

/* Создание объявления */
async function create_ads_func(req, res) {
	const title_form = req.body.title_form
    const cost_form = req.body.cost_form
    const descr_form = req.body.descr_form

	await client.connect();
	const db = client.db(dbName);
	const collection = db.collection('ads');
    
    const insertResult = await collection.insertMany([{ "title": title_form, "cost" : cost_form, "description" : descr_form }]);
    
    console.log(title_form, cost_form, descr_form)
}

app.get('/create_ad', (req, res) => {
	const data = JSON.parse(fs.readFileSync('public/create_ad.json'));
    const file = fs.readFileSync('public/template.html', 'utf-8');
    const template = mustache.render(file, data);
    
    res.send(template);
    
})

app.post('/create', urlencodedParser, (req, res) => {
    create_ads_func(req, res);
    res.redirect('/');
})

/* Удаление объявления */
async function delete_ad(id) {
	await client.connect();
	const db = client.db(dbName);
	const collection = db.collection('ads');
	
	if (id != '')
		await collection.deleteOne({_id: new bson.ObjectId (id)});
}

app.post('/delete', urlencodedParser, (req, res) => {
    console.log(req.body.id);
  	delete_ad(req.body.id);
  	res.redirect('/');
})

/* Поиск объявления */
app.get('/search', (req, res) => {
	const data = JSON.parse(fs.readFileSync('public/search.json'));
    const file = fs.readFileSync('public/template.html', 'utf-8');
    const template = mustache.render(file, data);
    
    res.send(template);
})

app.post('/search_ads', urlencodedParser, (req, res) => {
    search_ads(req, res);
})

async function search_ads(req, res) {
	const title_search = req.body.title_form
	// Use connect method to connect to the server
	await client.connect();
	const db = client.db(dbName);
	const collection = db.collection('ads');

	let data = {
		title: "Поиск",
		info: ""
	}
    const findResult = await collection.find({}).toArray();
	let info = '';
	for (let i = 0; i < findResult.length; i++)
	{
		if (findResult[i].title.indexOf(title_search) != -1) {
			let tmp = '<div class="ad"><span class="title">';
			tmp = tmp + findResult[i].title + '</span>';
			
			tmp = tmp + '<span class="cost">';
			tmp = tmp + findResult[i].cost + ' ₽</span>';
			
			tmp = tmp + '<span class="description">';
			tmp = tmp + findResult[i].description + '</span>';

			tmp = tmp + '<button class="btn btn-primary btn-md" value="' + findResult[i]._id + '" type="submit"><img src="/img/trash.png"></button></div>'; 
			info = info + tmp;
		}
	}
	
	data.info = info;
	const file = fs.readFileSync('public/template.html', 'utf-8');
    const template = mustache.render(file, data);
    
	res.send(template);
}

app.listen(port, host, () =>
{
    console.log(`Сайт готов к работе. Доступен по адресу http://${host}:${port}`);
});
