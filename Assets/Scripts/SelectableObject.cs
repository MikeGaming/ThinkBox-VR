using UnityEngine;
using UnityEngine.Events;

public class SelectableObject : MonoBehaviour
{
    [SerializeField] private UnityEvent onSelect;
    [SerializeField] private UnityEvent onDeselect;
    [SerializeField] private float HighlightScale = 1.2f;
    [SerializeField] private float HighlightLerpSpeed = 8f;
    [SerializeField] private Color selectedColor = Color.green;
    [SerializeField] private float selectedColorDuration = 1f;

    private bool isSelected = false;
    private bool highlightActive = false;
    private Vector3 originalScale;
    private Vector3 targetScale;
    private bool isHighlighted = false;
    private Color originalColor;
    private Renderer objectRenderer;
    private Coroutine colorCoroutine;

    private void Awake()
    {
        originalScale = transform.localScale;
        targetScale = originalScale;
        objectRenderer = GetComponent<Renderer>();
        if (objectRenderer != null)
        {
            originalColor = objectRenderer.material.color;
        }
    }

    private void Update()
    {
        Vector3 desiredScale = highlightActive ? originalScale * HighlightScale : originalScale;
        if (transform.localScale != desiredScale)
        {
            transform.localScale = Vector3.Lerp(transform.localScale, desiredScale, Time.deltaTime * HighlightLerpSpeed);
        }
    }

    public void SetHighlightActive(bool active)
    {
        highlightActive = active;
    }

    public void Select()
    {
        if (!isSelected)
        {
            isSelected = true;
            onSelect?.Invoke();
            SetHighlightActive(false);
            Debug.Log($"{gameObject.name} selected.");
            if (objectRenderer != null)
            {
                if (colorCoroutine != null)
                    StopCoroutine(colorCoroutine);
                colorCoroutine = StartCoroutine(FlashSelectedColor());
            }
        }
    }

    private System.Collections.IEnumerator FlashSelectedColor()
    {
        objectRenderer.material.color = selectedColor;
        yield return new WaitForSeconds(selectedColorDuration);
        objectRenderer.material.color = originalColor;
        colorCoroutine = null;
    }

    public void Deselect()
    {
        if (isSelected)
        {
            isSelected = false;
            onDeselect?.Invoke();
            SetHighlightActive(false);
            Debug.Log($"{gameObject.name} deselected.");
        }
    }

    public bool IsSelected()
    {
        return isSelected;
    }
}
