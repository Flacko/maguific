function isIdentifierCharacter(s)
{
	if(s>=65&&s<=90) //uppercase letters
	{
		return 1;
	}
	if(s>=97&&s<=122) //lowercase
	{
		return 1;
	}
	if(s==95) //underscore
	{
		return 1;
	}
	return 0;
}
function isNumberCharacter(s)
{
	if(s>=48 && s<=57)
	{
		return 1;
	}
	return 0;
}
function isDigitCharacter(s)
{
	if(isNumberCharacter(s)) //0123456789
	{
		return 1;
	}
	if(s==46) // .
	{
		return 1;
	}
	if(s==120) // x
	{
		return 1;
	}
	if(s==100 || s==102) // f and d suffixes
	{
		return 1;
	}
	if(s>=65 && s<=70) //ABCDEF for hex numbers
	{
		return 1;
	}
	return 0;
}
function isOperatorCharacter(s)
{
	var operators = new Array(
	"+","-","*","/","%","=",
	"|","&","^","!","~",
	";",",",".",
	"<",">",
	":","?",
	"(",")",
	"{","}",
	"[","]"
	);
	for(var i=0; i<operators.length; i++)
	{
		if(s==operators[i])
		{
			return 1;
		}
	}
	return 0;
}
function isKeyword(s)
{
	var keywords = new Array(
		"for","while","if","else","case","switch",
		"goto","continue","break","do",
		"void",
		"NULL",
		"signed","unsigned","long","short",
		"bool","char","int","float","double",
		"true","false",
		"new","delete",
		"sizeof","typeof",
		"and","or","not","xor",
		"const", "virtual",
		"class", "public", "private", "protected",
		"enum", "struct", "namespace", "typedef"
	);
	for(var i=0; i<keywords.length; i++)
	{
		if(s == keywords[i])
		{
			return 1;
		}
	}
	return 0;
}
function highlightSyntax(element)
{
	var origin = element.innerHTML;
	var txt = "";
		
	origin = origin.replace(/&gt;/g,">").replace(/&lt;/g,"<").replace(/&amp;/g,"&");
		
	for(var i=0; i<origin.length; i++)
	{
		var character = origin.charAt(i);
		var charcode = origin.charCodeAt(i);
		if(character == "\"" || character == "\'")
		{
			var quotechar = character;
			txt +="<span class='string'>";
			txt += character;
			i++;
			while(origin.charAt(i))
			{
				txt += origin.charAt(i);
				if(origin.charAt(i)=="\\")
				{
					if(origin.charAt(i+1) == quotechar)
					{
						i++;
						txt+=origin.charAt(i);
					}
				}
				else if(origin.charAt(i) == quotechar)
				{
					txt +="</span>";
					break;
				}
				i++;
			}
		}
		else if(character == "/" && (origin.charAt(i+1)=="/" || origin.charAt(i+1)=="*"))
		{
			if(origin.charAt(i+1)=="/")
			{
				txt+="<span class='comment'>";
				txt+=character;
				i++;
				while(origin.charAt(i))
				{
					txt += origin.charAt(i);
					if(origin.charAt(i) == "\n")
					{
						txt +="</span>";
						break;
					}
					i++;
				}
			}
			else if(origin.charAt(i+1)=="*")
			{
				txt+="<span class='comment'>";
				txt+=character;
				i++;
				while(origin.charAt(i))
				{
					txt+= origin.charAt(i);
					if(origin.charAt(i) == "/" && origin.charAt(i-1) == "*")
					{
						txt += "</span>";
						break;
					}
					i++;
				}
			}
		}
		else if(isIdentifierCharacter(charcode))
		{
			var word = character;
			i++
			while(isIdentifierCharacter(origin.charCodeAt(i))==1 ||  isNumberCharacter(origin.charCodeAt(i))==1)
			{
				word += origin.charAt(i);
				i++
			}
			if(isKeyword(word))
			{
				word = "<span class='keyword'>"+word+"</span>";
			}
			txt+=word;
			i--;
		}
		else if(isNumberCharacter(charcode))
		{
			txt+="<span class='number'>";
			txt+=character;
			i++;
			while(isDigitCharacter(origin.charCodeAt(i))==1)
			{
				txt+=origin.charAt(i)
				i++;
			}
			txt+="</span>"
			i--;
		}
		else if(character == "#")
		{
			txt += "<span class='preprocessor'>";
			txt+=character;
			i++;
			while(origin.charAt(i))
			{
				if(origin.charAt(i) == "<")
				{
					txt += "&lt;";
				}
				else if(origin.charAt(i) == ">")
				{
					txt += "&gt;";
				}
				else if(origin.charAt(i) == "&")
				{
					txt += "&amp;"
				}
				else
				{
					txt += origin.charAt(i);
				}
				if(origin.charAt(i) == "\n" && origin.charAt(i-1) != "\\")
				{
					break;
				}
				i++
			}
			txt+="</span>";
		}
		else if(isOperatorCharacter(character))
		{
			txt += "<span class='operator'>"+character+"</span>";
		}
		else
		{
			txt+=character;
		}
	}
	element.innerHTML = txt;
}