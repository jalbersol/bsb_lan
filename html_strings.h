#if defined(__SAM3X8E__)
const char favicon [] PROGMEM_LATE = { 
#else
const byte favicon [] PROGMEM_LATE = { 
#endif
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52,
  0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x91, 0x68,
  0x36, 0x00, 0x00, 0x00, 0x6c, 0x49, 0x44, 0x41, 0x54, 0x28, 0xcf, 0x95, 0x52, 0x41, 0x0e, 0xc0,
  0x20, 0x08, 0x03, 0xe2, 0xff, 0xbf, 0xcc, 0x0e, 0xdd, 0x18, 0xc1, 0x42, 0x42, 0x0f, 0xa6, 0x54,
  0xc0, 0x8a, 0xaa, 0x7c, 0x70, 0x77, 0x10, 0x55, 0xcd, 0x4a, 0x09, 0x5f, 0x86, 0x20, 0x56, 0xaa,
  0x80, 0x98, 0xf4, 0xf8, 0x5b, 0x26, 0xe8, 0xd6, 0x92, 0xe6, 0x8d, 0xd2, 0x12, 0x4a, 0xe8, 0x20,
  0x93, 0x25, 0x8a, 0x5a, 0x10, 0x06, 0x3a, 0xec, 0xef, 0x40, 0x47, 0x31, 0x59, 0xa2, 0x1e, 0xb2,
  0x58, 0xb8, 0xd1, 0x6c, 0x0c, 0x87, 0xd6, 0x18, 0xcd, 0x86, 0xe3, 0xec, 0x3e, 0xf8, 0x99, 0xfd,
  0xdc, 0x20, 0x05, 0xf7, 0xb8, 0xf2, 0x21, 0x8b, 0x87, 0x43, 0xa3, 0x23, 0xf4, 0x03, 0xf7, 0x78,
  0x00, 0x35, 0x57, 0x66, 0x05, 0xab, 0xf8, 0x2b, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e,
  0x44, 0xae, 0x42, 0x60, 0x82
};

const char graph_html[] PROGMEM_LATE =
//"<!--\n"
//"/*\n"
//"	Based on the awesome tutorials at\n"
//"		https://bl.ocks.org/d3noob\n"
//"		https://bl.ocks.org/larsenmtl\n"
//"	Thanks a lot for your great work!\n"
//"*/\n"
//"//-->\n"
"<style>\n"
"path {stroke:steelblue;stroke-width:2;fill:none;}\n"
".axis path,.axis line {fill:none;stroke:grey;stroke-width:1;shape-rendering:crispEdges;}\n"
".axis .tick line {stroke:#eee;}\n"
".legend {font-size:10px;font-weight:bold;text-anchor:middle;}\n"
"</style>\n"
//"<!-- load the d3.js library -->\n"
"<script src=\"http://d3js.org/d3.v3.min.js\"></script>\n"
"<script>\n"
"var searchParams=new URLSearchParams(window.location.search),maxWidth=1e3,maxHeight=500,minValue=Number.MIN_SAFE_INTEGER,maxValue=Number.MAX_SAFE_INTEGER,progYes=null,progNo=null,dateF=null,dateT=null;if(searchParams.has(\"w\")&&searchParams.get(\"w\")>1e3&&(maxWidth=searchParams.get(\"w\")),searchParams.has(\"h\")&&searchParams.get(\"h\")>300&&(maxHeight=searchParams.get(\"h\")),searchParams.has(\"min\")&&(minValue=searchParams.get(\"min\")),searchParams.has(\"max\")&&(maxValue=searchParams.get(\"max\")),searchParams.has(\"p\")&&(progYes=searchParams.get(\"p\")),searchParams.has(\"q\")&&(progNo=searchParams.get(\"q\")),searchParams.has(\"f\")){var f=searchParams.get(\"f\");f.match(/[+-]?\\d+/)?(dateF=new Date).setDate(dateF.getDate()-Math.abs(parseInt(f))):f.length>0&&(dateF=new Date(searchParams.get(\"f\")))}searchParams.has(\"t\")&&searchParams.get(\"t\").length>0&&(dateT=new Date(searchParams.get(\"t\")+\" 23:59:59\"));var margin={top:30,right:20,bottom:70,left:50},width=maxWidth-margin.left-margin.right,height=maxHeight-margin.top-margin.bottom,parseDate=d3.time.format(\"%d.%m.%Y %H:%M:%S\").parse,x=d3.time.scale().range([0,width]),y=d3.scale.linear().range([height,0]),axisTimeFormat=d3.time.format.multi([[\".%L\",function(e){return e.getMilliseconds()}],[\":%S\",function(e){return e.getSeconds()}],[\"%H:%M\",function(e){return e.getMinutes()}],[\"%H:%M\",function(e){return e.getHours()}],[\"%d.%m\",function(e){return e.getDay()&&1!=e.getDate()}],[\"%m.%Y\",function(e){return 1!=e.getDate()}],[\"%B\",function(e){return e.getMonth()}],[\"%Y\",function(){return!0}]]),xAxis=d3.svg.axis().scale(x).orient(\"bottom\").ticks(5).tickSize(-height,0,0).tickFormat(axisTimeFormat),yAxis=d3.svg.axis().scale(y).orient(\"left\").ticks(10).tickSize(-width,0,0),priceline=d3.svg.line().x(function(e){return x(e.Date)}).y(function(e){return y(e.Value)}),dsv=d3.dsv(\";\",\"text/plain\");dsv(\"D\",function(e){progYes&&(e=e.filter(e=>progYes.includes(e.Parameter))),progNo&&(e=e.filter(e=>!progNo.includes(e.Parameter))),e.forEach(function(e){e.Date=parseDate(e.Date),e.Value=+e.Value,e.Value<minValue&&(e.Value=minValue),e.Value>maxValue&&(e.Value=maxValue)}),dateF&&(e=e.filter(e=>e.Date>=dateF)),dateT&&(e=e.filter(e=>e.Date<=dateT)),x.domain(d3.extent(e,function(e){return e.Date})),y.domain([d3.min(e,function(e){return e.Value}),d3.max(e,function(e){return e.Value})]);var t=d3.nest().key(function(e){return e.Description+\" (\"+e.Parameter+\")\"}).entries(e),a=d3.select(\"div\").append(\"svg\").attr(\"width\",width+margin.left+margin.right).attr(\"height\",height+margin.top+margin.bottom+t.length/4*15).append(\"g\").attr(\"transform\",\"translate(\"+margin.left+\",\"+margin.top+\")\");a.append(\"g\").attr(\"class\",\"x axis\").attr(\"transform\",\"translate(0,\"+height+\")\").call(xAxis),a.append(\"g\").attr(\"class\",\"y axis\").call(yAxis);var r=d3.scale.category10();legendSpace=width/t.length,t.forEach(function(e,t){a.append(\"path\").attr(\"class\",\"line\").style(\"stroke\",function(){return e.color=r(e.key)}).attr(\"id\",\"tag\"+e.key.replace(/\\s+/g,\"\")).attr(\"d\",priceline(e.values)),a.append(\"text\").attr(\"x\",margin.left+legendSpace/2+t%4*width/4).attr(\"y\",height+margin.bottom/2+5+20*Math.floor(t/4)).attr(\"class\",\"legend\").style(\"fill\",function(){return e.color=r(e.key)}).on(\"click\",function(){var t=!e.active,a=t?0:1;d3.select(\"#tag\"+e.key.replace(/\\s+/g,\"\")).transition().duration(100).style(\"opacity\",a),e.active=t}).text(e.key)});var n=a.append(\"g\").attr(\"class\",\"mouse-over-effects\");n.append(\"path\").attr(\"class\",\"mouse-line\").style(\"stroke\",\"black\").style(\"stroke-width\",\"1px\").style(\"opacity\",\"0\");var s=document.getElementsByClassName(\"line\"),i=n.selectAll(\".mouse-per-line\").data(t).enter().append(\"g\").attr(\"class\",\"mouse-per-line\");i.append(\"circle\").attr(\"r\",7).attr(\"id\",function(e){return\"tag\"+e.key.replace(/\\s+/g,\"\")}).style(\"stroke\",function(e){return r(e.key)}).style(\"fill\",\"none\").style(\"stroke-width\",\"1px\").style(\"opacity\",\"0\"),i.append(\"text\").attr(\"id\",function(e){return\"tag\"+e.key.replace(/\\s+/g,\"\")}).attr(\"transform\",\"translate(10,3)\"),n.append(\"svg:rect\").attr(\"width\",width).attr(\"height\",height).attr(\"fill\",\"none\").attr(\"pointer-events\",\"all\").on(\"mouseout\",function(){d3.select(\".mouse-line\").style(\"opacity\",\"0\"),d3.selectAll(\".mouse-per-line circle\").style(\"opacity\",\"0\"),d3.selectAll(\".mouse-per-line text\").style(\"opacity\",\"0\")}).on(\"mouseover\",function(){d3.select(\".mouse-line\").style(\"opacity\",\"1\"),d3.selectAll(\".mouse-per-line circle\").style(\"opacity\",function(e){return e.active?0:1}),d3.selectAll(\".mouse-per-line text\").style(\"opacity\",function(e){return e.active?0:1})}).on(\"mousemove\",function(){var e=d3.mouse(this);d3.select(\".mouse-line\").attr(\"d\",function(){var t=\"M\"+e[0]+\",\"+height;return t+=\" \"+e[0]+\",0\"}),d3.selectAll(\".mouse-per-line\").attr(\"transform\",function(t,a){var r=x.invert(e[0]),n=d3.bisector(function(e){return e.Date}).right;idx=n(t.values,r);for(var i=0,l=s[a].getTotalLength(),o=null;o=Math.floor((i+l)/2),pos=s[a].getPointAtLength(o),o!==l&&o!==i||pos.x===e[0];)if(pos.x>e[0])l=o;else{if(!(pos.x<e[0]))break;i=o}return outputFormat=d3.time.format(\"%H:%M:%S\"),t.values[idx]&&d3.select(this).select(\"text\").text(t.values[idx].Value+\" (\"+outputFormat(t.values[idx].Date)+\")\"),\"translate(\"+e[0]+\",\"+pos.y+\")\"})})});\n"
"</script>\n";

const char header_html[] PROGMEM_LATE = 
  "HTTP/1.1 200 OK\n"
  "Content-Type: text/html\n"
  "Cache-Control: no-cache, no-store, must-revalidate\n"
  "Pragma: no-cache\n"
  "Expires: 0\n"
  "Connection: close\n"
  "\n"
  "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\">\n"
  "<html><head>\n"
  "<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">\n"
  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0\">\n"
  "<title>BSB-LAN Web</title>\n"
  "<style>A:link {color:blue;text-decoration:none;} A:visited {color:blue;text-decoration:none;} A:hover {color:red;text-decoration:none;background-color:yellow} A:active {color:blue;text-decoration:none;} A:focus {color:red;text-decoration:none;}\n"
  "input {width:100%;box-sizing:border-box;} select {width:100%;}\n"
  "html {font-family:sans-serif;}\n"
  "table {max-width:1024px;width:100%;}\n"
  "hr {max-width:1024px;border:1px solid #f0f0f0;}\n"
  "</style>\n"
  "</head><body>\n"
  "<script>function set(line){\n"
  "var value=document.getElementById('value'+line).value.replace(\":\", \".\");\n"
  "value=value.replace(\"---\", \"\");\n"
  "if(isNaN(value)==false||value==''){\n"
  "window.open(document.getElementById('main_link').href+'S'+line+'='+value,'_self');\n"
  "}}\n"
  "function setbit(line){\n"
  "var x=document.getElementById('value'+line); var value=0;\n"
  "for(var i=0;i<x.options.length;i++) {if(x.options[i].selected){value=value+eval(x.options[i].value);}}\n"
  "window.open(document.getElementById('main_link').href+'S'+line+'='+value,'_self');\n"
  "}</script>\n"
  "<center><h1><A ID=main_link HREF='/";

const char auth_req_html[] PROGMEM_LATE = 
  "HTTP/1.1 401 Authorization Required\n"
  "WWW-Authenticate: Basic realm=\"Secure Area\"\n"
  "Content-Type: text/html\n"
  "Connnection: close\n"
  "\n"
  "<!DOCTYPE HTML>\n"
  "<HTML><HEAD><TITLE>Error</TITLE>"
  "</HEAD><BODY><H1>401 Unauthorized.</H1></BODY></HTML>";
