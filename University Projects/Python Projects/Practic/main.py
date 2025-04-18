from Repository.automobile import Automobile
from Service.services import ServicesAutomobile
from UI.console import Console

repository = Automobile("Data/automobile")
service = ServicesAutomobile(repository)
Console.run(service)