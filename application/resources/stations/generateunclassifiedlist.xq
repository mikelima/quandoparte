<stations>
{
for $doc in ('nord.osm',
             'nordovest.osm', 
             'nordest.osm',
	     'liguria.osm',
             'centronord.osm', 
	     'centrosud.osm', 
	     'sud.osm', 
	     'sicilia.osm', 
	     'puglia.osm', 
	     'sardegna.osm')
for $node in doc($doc)//node
where $node/tag[@k='name'] and empty($node/tag[@k='operator']) 
return 
<station>
<pos>{
data($node/@lon)
},{
data($node/@lat)
}
</pos>
<name>
{
data($node//tag[@k='name']/@v)
}
</name>
<id>
{
data($node/@id)
}
</id>
</station>
}
</stations>
