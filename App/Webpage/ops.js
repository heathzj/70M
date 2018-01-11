function onloadConfig()
{
	try
	{
		checkDHCP();
		checkMODE();
	}
	catch(e){}
}

function checkDHCP()
{
	try
	{
		var chk = document.getElementById('dhcp');
		var res = chk.checked;
		var ip = document.getElementById('DIP');
		var gw = document.getElementById('gateway');
		var snet = document.getElementById('subnet');
		var bip = document.getElementById('btnDIP');
		var bgw = document.getElementById('btnGateway');
		var bsnet = document.getElementById('btnSubnet');
		
		if( res )
		{
			ip.disabled = true;
			gw.disabled = true;
			snet.disabled = true;
			bip.disabled = true;
			bgw.disabled = true;
			bsnet.disabled = true;
		}
		else
		{
			ip.disabled = false;
			gw.disabled = false;
			snet.disabled = false;
			bip.disabled = false;
			bgw.disabled = false;
			bsnet.disabled = false;
		}
	}
	catch(e){}
}

function checkMODE()
{
	try
	{
		var chk = document.getElementById('swmode');
		var chosenoption=chk.options[chk.selectedIndex];
		var p = document.getElementById('onlinepath');		
		
		if (chosenoption.textContent != "nothing"){
			if(chosenoption.textContent == "Auto")
			{
				p.disabled = true;
			}
			else
			{
				p.disabled = false;
			}
		}
		
	}
	catch(e){}
}
