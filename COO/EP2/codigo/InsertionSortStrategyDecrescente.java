import java.util.Comparator;
import java.util.List;

public class InsertionSortStrategyDecrescente implements OrdenacaoStrategy {
    private Comparator<Produto> comparator;

    public InsertionSortStrategyDecrescente(Comparator<Produto> comparator) {
        this.comparator = comparator.reversed();
    }

    @Override
    public void ordena(List<Produto> produtos) {
        for (int i = 1; i < produtos.size(); i++) {
            Produto x = produtos.get(i);
            int j = i - 1;
            while (j >= 0 && comparator.compare(produtos.get(j), x) > 0) {
                produtos.set(j + 1, produtos.get(j));
                j--;
            }
            produtos.set(j + 1, x);
        }
    }
}