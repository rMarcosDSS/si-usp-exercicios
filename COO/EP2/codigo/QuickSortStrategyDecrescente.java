import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class QuickSortStrategyDecrescente implements OrdenacaoStrategy {
    private Comparator<Produto> comparator;

    public QuickSortStrategyDecrescente(Comparator<Produto> comparator) {
        this.comparator = comparator.reversed();
    }

    @Override
    public void ordena(List<Produto> produtos) {
        quickSort(produtos, 0, produtos.size() - 1);
    }

    private void quickSort(List<Produto> produtos, int ini, int fim) {
        if (ini < fim) {
            int q = particiona(produtos, ini, fim);
            quickSort(produtos, ini, q);
            quickSort(produtos, q + 1, fim);
        }
    }

    private int particiona(List<Produto> produtos, int ini, int fim) {
        Produto x = produtos.get(ini);
        int i = ini - 1;
        int j = fim + 1;

        while (true) {
            do { j--; } while (comparator.compare(produtos.get(j), x) > 0);
            do { i++; } while (comparator.compare(produtos.get(i), x) < 0);

            if (i < j) {
                Collections.swap(produtos, i, j);
            } else {
                return j;
            }
        }
    }
}