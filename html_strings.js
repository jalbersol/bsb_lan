// 1. Minify via https://javascript-minifier.com/
// 2. Save .html_strings_opt.js
// 3. Replace all " with \"
// 4. Repace code in html_strings.h (line 51)

var searchParams = new URLSearchParams(window.location.search);
var maxWidth = 1000;
var maxHeight = 500;
var minValue = Number.MIN_SAFE_INTEGER;
var maxValue = Number.MAX_SAFE_INTEGER;
var progYes = null;
var progNo = null;
var dateF = null;
var dateT = null;
if (searchParams.has('w') && searchParams.get('w') > 1000) maxWidth = searchParams.get('w');
if (searchParams.has('h') && searchParams.get('h') > 300) maxHeight = searchParams.get('h');
if (searchParams.has('min')) minValue = searchParams.get('min');
if (searchParams.has('max')) maxValue = searchParams.get('max');
if (searchParams.has('p')) progYes = searchParams.get('p');
if (searchParams.has('q')) progNo = searchParams.get('q');
if (searchParams.has('f')) {
	var f = searchParams.get('f');
	if (f.match(/[+-]?\\d+/)) {
		dateF = new Date();
		dateF.setDate(dateF.getDate() - Math.abs(parseInt(f)));
	} else if (f.length > 0) dateF = new Date(searchParams.get('f'));
}
if (searchParams.has('t') && searchParams.get('t').length > 0) dateT = new Date(searchParams.get('t') + " 23:59:59");

// Set the dimensions of the canvas/graph
var margin = { top: 30, right: 20, bottom: 70, left: 50 },
	width = maxWidth - margin.left - margin.right,
	height = maxHeight - margin.top - margin.bottom;

// Parse the date/time
var parseDate = d3.time.format("%d.%m.%Y %H:%M:%S").parse;

// Set the ranges
var x = d3.time.scale().range([0, width]);
var y = d3.scale.linear().range([height, 0]);

// Define the axes
var axisTimeFormat = d3.time.format.multi([
	[".%L", function (d) { return d.getMilliseconds(); }],
	[":%S", function (d) { return d.getSeconds(); }],
	["%H:%M", function (d) { return d.getMinutes(); }],
	["%H:%M", function (d) { return d.getHours(); }],
	["%d.%m", function (d) { return d.getDay() && d.getDate() != 1; }],
	["%m.%Y", function (d) { return d.getDate() != 1; }],
	["%B", function (d) { return d.getMonth(); }],
	["%Y", function () { return true; }]
]);

var xAxis = d3.svg.axis().scale(x)
	.orient("bottom").ticks(5)
	.tickSize(-height, 0, 0)
	.tickFormat(axisTimeFormat);

var yAxis = d3.svg.axis().scale(y)
	.orient("left").ticks(10)
	.tickSize(-width, 0, 0);

// Define the line
var priceline = d3.svg.line()
	.x(function (d) { return x(d.Date); })
	.y(function (d) { return y(d.Value); });

// Get the data
var dsv = d3.dsv(";", "text/plain");
dsv("D", function (data) {

	if (progYes) data = data.filter(d => progYes.includes(d.Parameter));
	if (progNo) data = data.filter(d => !progNo.includes(d.Parameter));
	data.forEach(function (d) {
		d.Date = parseDate(d.Date);
		d.Value = +d.Value;
		if (d.Value < minValue) d.Value = minValue;
		if (d.Value > maxValue) d.Value = maxValue;
	});

	if (dateF) data = data.filter(d => d.Date >= dateF);
	if (dateT) data = data.filter(d => d.Date <= dateT);

	// Scale the range of the data
	x.domain(d3.extent(data, function (d) { return d.Date; }));
	y.domain([d3.min(data, function (d) { return d.Value; }), d3.max(data, function (d) { return d.Value; })]);

	// Nest the entries by symbol
	var dataNest = d3.nest()
		.key(function (d) { return d.Description + ' (' + d.Parameter + ')'; })
		.entries(data);

	// Adds the svg canvas
	var svg = d3.select("div")
		.append("svg")
		.attr("width", width + margin.left + margin.right)
		.attr("height", height + margin.top + margin.bottom + dataNest.length / 4 * 15)
		.append("g")
		.attr("transform", "translate(" + margin.left + "," + margin.top + ")");

	// Add the X Axis\n"     // axis behind data
	svg.append("g")
		.attr("class", "x axis")
		.attr("transform", "translate(0," + height + ")")
		.call(xAxis);

	// Add the Y Axis
	svg.append("g")
		.attr("class", "y axis")
		.call(yAxis);

	var color = d3.scale.category10();   // set the colour scale

	legendSpace = width / dataNest.length; // spacing for the legend

	// Loop through each symbol/key
	dataNest.forEach(function (d, i) {

		svg.append("path")
			.attr("class", "line")
			.style("stroke", function () { // Add the colours dynamically
				return d.color = color(d.key);
			})
			.attr("id", 'tag' + d.key.replace(/\\s+/g, '')) // assign ID
			.attr("d", priceline(d.values));

		// Add the Legend
		svg.append("text")
			.attr("x", (margin.left + legendSpace / 2 + (i % 4) * width / 4))  // space legend
			.attr("y", height + (margin.bottom / 2) + 5 + Math.floor(i / 4) * 20)
			.attr("class", "legend")    // style the legend
			.style("fill", function () { // Add the colours dynamically
				return d.color = color(d.key);
			})
			.on("click", function () {
				// Determine if current line is visible 
				var active = d.active ? false : true,
					newOpacity = active ? 0 : 1;
				// Hide or show the elements based on the ID
				d3.select("#tag" + d.key.replace(/\\s+/g, ''))
					.transition().duration(100)
					.style("opacity", newOpacity);
				// Update whether or not the elements are active
				d.active = active;
			})
			.text(d.key);
	});

	var mouseG = svg.append("g")
		.attr("class", "mouse-over-effects");

	mouseG.append("path") // this is the black vertical line to follow mouse
		.attr("class", "mouse-line")
		.style("stroke", "black")
		.style("stroke-width", "1px")
		.style("opacity", "0");

	var lines = document.getElementsByClassName('line');

	var mousePerLine = mouseG.selectAll('.mouse-per-line')
		.data(dataNest)
		.enter()
		.append("g")
		.attr("class", "mouse-per-line");

	mousePerLine.append("circle")
		.attr("r", 7)
		.attr("id", function (d) {
			return 'tag' + d.key.replace(/\\s+/g, '')	// assign ID
		})
		.style("stroke", function (d) {
			return color(d.key);
		})
		.style("fill", "none")
		.style("stroke-width", "1px")
		.style("opacity", "0");

	mousePerLine.append("text")
		.attr("id", function (d) {
			return 'tag' + d.key.replace(/\\s+/g, '')	// assign ID
		})
		.attr("transform", "translate(10,3)");

	mouseG.append('svg:rect') // append a rect to catch mouse movements on canvas
		.attr('width', width) // can't catch mouse events on a g element
		.attr('height', height)
		.attr('fill', 'none')
		.attr('pointer-events', 'all')
		.on('mouseout', function () { // on mouse out hide line, circles and text
			d3.select(".mouse-line")
				.style("opacity", "0");
			d3.selectAll(".mouse-per-line circle")
				.style("opacity", "0");
			d3.selectAll(".mouse-per-line text")
				.style("opacity", "0");
		})
		.on('mouseover', function () { // on mouse in show line, circles and text
			d3.select(".mouse-line")
				.style("opacity", "1");
			d3.selectAll(".mouse-per-line circle")
				.style("opacity", function (d) {
					return d.active ? 0 : 1;;
				});
			d3.selectAll(".mouse-per-line text")
				.style("opacity", function (d) {
					return d.active ? 0 : 1;;
				});
		})
		.on('mousemove', function () { // mouse moving over canvas
			var mouse = d3.mouse(this);
			d3.select(".mouse-line")
				.attr("d", function () {
					var d = "M" + mouse[0] + "," + height;
					d += " " + mouse[0] + "," + 0;
					return d;
				});

			d3.selectAll(".mouse-per-line")
				.attr("transform", function (d, i) {
					var xDate = x.invert(mouse[0]),
						bisect = d3.bisector(function (d) { return d.Date; }).right;
					idx = bisect(d.values, xDate);

					var beginning = 0,
						end = lines[i].getTotalLength(),
						target = null;

					while (true) {
						target = Math.floor((beginning + end) / 2);
						pos = lines[i].getPointAtLength(target);
						if ((target === end || target === beginning) && pos.x !== mouse[0]) {
							break;
						}
						if (pos.x > mouse[0]) end = target;
						else if (pos.x < mouse[0]) beginning = target;
						else break; //position found
					}

					outputFormat = d3.time.format("%H:%M:%S");
					if (d.values[idx])
						d3.select(this).select('text')
							.text(d.values[idx].Value + " (" + outputFormat(d.values[idx].Date) + ")");

					return "translate(" + mouse[0] + "," + pos.y + ")";
				});
		});
});
