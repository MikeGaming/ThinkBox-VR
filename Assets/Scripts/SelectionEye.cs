using UnityEngine;

public class SelectionEye : MonoBehaviour
{
    public bool selecting { get; set; } = false;
    public SelectableObject selectedObject { get; private set; }

    private void Update()
    {
        Debug.DrawRay(transform.position, transform.forward * 100f, Color.red);

        RaycastHit hit;
        int layerMask = ~(1 << 8);
        if (Physics.Raycast(transform.position, transform.forward, out hit, 100f, layerMask))
        {
            var selectable = hit.collider.GetComponent<SelectableObject>();
            if (selectable != null)
            {
                selecting = true;
                selectedObject = selectable;
                return;
            }
        }

        selecting = false;
        selectedObject = null;
    }
    public void ClearSelection()
    {
        selecting = false;
        selectedObject = null;
    }

    
}
