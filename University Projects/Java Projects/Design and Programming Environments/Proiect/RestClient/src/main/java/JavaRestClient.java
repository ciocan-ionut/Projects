import app.model.SwimmingTest;
import org.springframework.http.client.ClientHttpRequestInterceptor;
import org.springframework.web.client.RestClient;

public class JavaRestClient {
    public static void main(String[] args) {
        ClientHttpRequestInterceptor loggingInterceptor = (request, body, execution) -> {
            System.out.println("Request trimis: " + request.getMethod() + " " + request.getURI());
            var response = execution.execute(request, body);
            System.out.println("Raspuns primit: Status " + response.getStatusCode());
            return response;
        };

        RestClient restClient = RestClient.builder()
                .baseUrl("http://localhost:8081/api/probe")
                .requestInterceptor(loggingInterceptor)
                .build();

        SwimmingTest proba = new SwimmingTest(null, 10000, "liber");
        Integer generatedId = restClient.post()
                .body(proba)
                .header("Content-Type", "application/json")
                .retrieve()
                .body(Integer.class);

        System.out.println("Proba a fost creata cu ID-ul: " + generatedId);

        String testCautat = restClient.get()
                .uri("/" + generatedId)
                .retrieve()
                .body(String.class);

        System.out.println("Proba gasita: " + testCautat);
    }
}