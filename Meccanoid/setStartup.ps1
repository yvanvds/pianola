if (!([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) 
{ 
   Start-Process powershell.exe "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`"" -Verb RunAs; exit 
}

[void][Reflection.Assembly]::LoadWithPartialName('Microsoft.VisualBasic')

$title = 'Meccanoid Setup'
$msg   = "Enter the Meccanoid's IP-Address:"

$address = [Microsoft.VisualBasic.Interaction]::InputBox($msg, $title)

net start WinRM -quiet

Set-Item WSMan:\localhost\Client\TrustedHosts -Value $address -Confirm:$false
$s = New-PSSession -ComputerName $address -Credential $address\Administrator

if(-not($s)) {
    [System.Windows.Forms.MessageBox]::Show("Unable to connect")
    exit
} else {
    Invoke-Command -Session $s -ScriptBlock { IoTStartup add headed Meccanoid* }
    Invoke-Command -Session $s -ScriptBlock { shutdown /r /t 0 }
    [System.Windows.Forms.MessageBox]::Show("The meccanoid will now reboot.")
}

Remove-PSSession $s

Write-Host "Press any key to continue ..."

$x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")





