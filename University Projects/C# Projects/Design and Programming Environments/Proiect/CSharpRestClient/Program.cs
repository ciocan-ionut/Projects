using model;
using System;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Net.Http.Json;

public class LoggingHandler : DelegatingHandler
{
    public LoggingHandler(HttpMessageHandler innerHandler) : base(innerHandler) { }

    protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
    {
        Console.WriteLine($"Request trimis: {request.Method} {request.RequestUri}");
        var response = await base.SendAsync(request, cancellationToken);
        Console.WriteLine($"Raspuns primit: Status {response.StatusCode}");
        return response;
    }
}

class Program
{
    static async Task Main(string[] args)
    {
        var client = new HttpClient(new LoggingHandler(new HttpClientHandler()))
        {
            BaseAddress = new Uri("http://localhost:8081/api/probe")
        };

        SwimmingTest proba = new SwimmingTest(0, 10000, "liber");
        var postResponse = await client.PostAsJsonAsync("", proba);
        var generatedId = await postResponse.Content.ReadAsStringAsync();
        Console.WriteLine($"Proba a fost creata cu ID-ul: {generatedId}");

        var getResponse = await client.GetAsync("?style=spate");
        var body = await getResponse.Content.ReadAsStringAsync();
        Console.WriteLine($"Probele filtrate gasite: {body}");
    }
}